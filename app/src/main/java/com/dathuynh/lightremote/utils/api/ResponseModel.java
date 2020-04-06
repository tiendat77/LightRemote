package com.dathuynh.lightremote.utils.api;

import com.google.gson.annotations.SerializedName;

public class ResponseModel {

  @SerializedName("light1")
  private boolean light1;

  @SerializedName("light2")
  private boolean light2;

  public boolean getLight1() {
    return light1;
  }

  public boolean getLight2() {
    return light2;
  }
}
