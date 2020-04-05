package com.dathuynh.lightremote.ui.wifi;

import androidx.lifecycle.ViewModelProviders;

import android.os.AsyncTask;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import com.dathuynh.lightremote.R;
import com.google.android.material.floatingactionbutton.FloatingActionButton;

public class wifi extends Fragment implements View.OnClickListener {

  // DECLARE VARIABLES
  private static String TAG = "Wifi Remote";
  private WifiViewModel mViewModel;
  private FloatingActionButton lightButton1;
  private FloatingActionButton lightButton2;
  private FloatingActionButton lightButton3;
  private FloatingActionButton lightButton4;

  private Boolean light1;
  private Boolean light2;

  private SocketClient socketClient;

  public static wifi newInstance() {
    return new wifi();
  }

  @Override
  public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                           @Nullable Bundle savedInstanceState) {
    View view = inflater.inflate(R.layout.wifi_fragment, container, false);

    // INITIALIZE
    initView(view);
    initVariable();
    initListener();

    return view;
  }

  @Override
  public void onActivityCreated(@Nullable Bundle savedInstanceState) {
    super.onActivityCreated(savedInstanceState);
    mViewModel = ViewModelProviders.of(this).get(WifiViewModel.class);
  }

  @Override
  public void onClick(View v) {
    switch (v.getId()) {
      case R.id.wifi_button_func1:
        onCLickLight1();
        break;

      case R.id.wifi_button_func2:
        onCLickLight2();
        break;

      default:
        pushNotify("Command not found!");
        break;
    }
  }

  // INIT
  private void initView(View view) {
    lightButton1 = view.findViewById(R.id.wifi_button_func1);
    lightButton2 = view.findViewById(R.id.wifi_button_func2);
    lightButton3 = view.findViewById(R.id.wifi_button_func3);
    lightButton4 = view.findViewById(R.id.wifi_button_func4);

    lightButton1.setImageResource(R.drawable.ic_led_off);
    lightButton2.setImageResource(R.drawable.ic_light_bulb_off);
    lightButton3.setImageResource(R.drawable.ic_led_off);
    lightButton4.setImageResource(R.drawable.ic_light_bulb_off);
  }

  private void initListener() {
    lightButton1.setOnClickListener(this);
    lightButton2.setOnClickListener(this);
    lightButton3.setOnClickListener(this);
    lightButton4.setOnClickListener(this);
  }

  private void initVariable() {
    light1 = false;
    light2 = false;
  }

  // HANDLER
  private void onCLickLight1() {
    light1 = !light1;

    if (light1) {
      lightButton1.setImageResource(R.drawable.ic_led_on);
    } else {
      lightButton1.setImageResource(R.drawable.ic_led_off);
    }
  }

  private void onCLickLight2() {
    light2 = !light2;

    if (light2) {
      lightButton2.setImageResource(R.drawable.ic_light_bulb_on);
    } else {
      lightButton2.setImageResource(R.drawable.ic_light_bulb_off);
    }
  }

  private void onReceiveMessage(String message) {
    Log.d(TAG, message);
  }

  // UTILS
  public class RemoteControlTask extends AsyncTask<String, String, String> {
    @Override
    protected String doInBackground(String... message) {
      createSocket();
      return null;
    }
  }

  private void createSocket() {
    socketClient = new SocketClient(new SocketClient.OnReceiveMessage() {
      @Override
      public void receivedMessage(String message) {
        onReceiveMessage(message);
      }
    });

    if (socketClient != null) {
      socketClient.start();
    }
  }

  private void pushNotify(String message) {
    Toast.makeText(getContext(), message, Toast.LENGTH_SHORT).show();
  }
}
