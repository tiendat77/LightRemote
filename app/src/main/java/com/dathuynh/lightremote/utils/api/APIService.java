package com.dathuynh.lightremote.utils.api;

public class APIService {
  public static String SERVER_API_BASE = "http://192.168.1.105/api/";

  public static API createAPIService() {
    return RetrofitClient.getRetrofitService(SERVER_API_BASE).create(API.class);
  }
}
