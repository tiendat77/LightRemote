package com.dathuynh.lightremote.utils.api;

import com.google.gson.annotations.SerializedName;

public class ResponseModel {

  @SerializedName("light1")
  private LightModel light1;

  @SerializedName("light2")
  private LightModel light2;

  public LightModel getLight1() {
    return light1;
  }

  public LightModel getLight2() {
    return light2;
  }
}
