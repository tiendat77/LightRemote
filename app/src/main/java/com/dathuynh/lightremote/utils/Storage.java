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
    String serverIp = preferences.getString("signature", "");
    return serverIp;
  }
}
