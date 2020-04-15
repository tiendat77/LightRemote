package com.dathuynh.lightremote.utils.api;

import com.google.gson.annotations.SerializedName;

public class ResponseModel {

  @SerializedName("light1")
  private int light1;

  @SerializedName("light2")
  private int light2;

  public boolean getLight1() {
    return (light1 == 1);
  }

  public boolean getLight2() {
    return (light2 == 1);
  }
}
