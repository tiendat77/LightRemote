package com.dathuynh.lightremote.utils.api;

import retrofit2.Call;
import retrofit2.http.GET;

public interface API {

  @GET("status")
  Call<ResponseModel> getLightStatus();

}
