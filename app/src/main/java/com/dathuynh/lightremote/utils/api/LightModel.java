package com.dathuynh.lightremote.utils.api;

import com.google.gson.annotations.SerializedName;

public class LightModel {

  /*
  * Light status:
  * 0: Light Off
  * 1: Light On
  * */
  @SerializedName("status")
  private boolean status;

  public boolean getStatus() {
    return this.status;
  }
}
