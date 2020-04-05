package com.dathuynh.lightremote.ui.wifi;

import android.util.Log;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;

public class SocketClient {
  private static String TAG = "Socket Client";

  private Socket socket;
  private String serverIp;
  private boolean isRunning = false;

  private String receiveMessage;
  private OnReceiveMessage receiver = null;

  BufferedReader reader;
  PrintWriter writer;

  public SocketClient(OnReceiveMessage messageListener) {
    this.receiver = messageListener;
    this.serverIp = Constants.SERVER_IP;
  }

  /**
   * Sends the message entered by client to the server
   *
   * @param message text entered by client
   */
  public void sendMessage(final String message) {
    new Thread(new Runnable() {
      @Override
      public void run() {
        try {
          if (writer != null) {
            writer.println(message);
          }

        } catch (Exception e) {
          e.printStackTrace();
        }
      }
    }).start();
  }

  public void stop() {
    isRunning = false;
    try {
      socket.close();

    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  public void start() {
    isRunning = true;

    try {
      InetAddress serverAddress = InetAddress.getByName(serverIp);
      Log.d(TAG, "Connecting to" + serverAddress.toString());

      socket = new Socket(serverAddress, Constants.SERVER_PORT);

      try {
        Log.d(TAG, "Connected " + serverAddress.toString());

        reader = new BufferedReader(new InputStreamReader(
            socket.getInputStream()));

        writer = new PrintWriter(new BufferedWriter(
            new OutputStreamWriter(socket.getOutputStream())),
            true);

        // in this while the client listens for the messages sent by the server
        while (isRunning) {
          receiveMessage = reader.readLine();

          if (receiveMessage != null && receiver != null) {
            receiver.receivedMessage(receiveMessage);
          }

          receiveMessage = null;
        }

      } catch (Exception e) {
        Log.wtf(TAG, "Error ", e);

      } finally {
        socket.close();
      }

    } catch (Exception e) {
      Log.wtf(TAG, "Error ", e);
    }
  }

  // Declare the interface. The method messageReceived(String message)
  // must be implemented in the Activity
  // at asyncTask doInBackground
  public interface OnReceiveMessage {
    void receivedMessage(String message);
  }
}
