package com.dathuynh.lightremote.utils;

import android.content.Context;
import android.content.SharedPreferences;

import androidx.preference.PreferenceManager;

public class Storage {
  private SharedPreferences preferences;
  private Context context;

  public Storage(Context context) {
    this.context = context;
    this.preferences = PreferenceManager.getDefaultSharedPreferences(context);
  }

  public String getServerIp() {
    String serverIp = preferences.getString("server_ip", "");
    return serverIp;
  }

  public boolean getTheme() {
    boolean darkTheme = preferences.getBoolean("theme", false);
    return darkTheme;
  }
}
