package com.dathuynh.lightremote.utils.api;

import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Query;

public interface API {

  @GET("/api/list")
  Call<ResponseModel> getLightStatus();

  @GET("/api/update/light1")
  Call<ResponseModel> updateLight1Status(@Query("status") String status);

  @GET("/api/update/light2")
  Call<ResponseModel> updateLight2Status(@Query("status") String status);

}
