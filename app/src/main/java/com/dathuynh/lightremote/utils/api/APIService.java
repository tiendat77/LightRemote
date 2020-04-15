package com.dathuynh.lightremote.utils.api;

public class APIService {
  public static String SERVER_API_BASE = "http://192.168.1.105";

  public static API createAPIService(String serverAddress) {
    String SERVER_API_URL = SERVER_API_BASE;

    if (!serverAddress.equals("")) {
      SERVER_API_URL = serverAddress;
    }

    return RetrofitClient.getRetrofitService(SERVER_API_URL).create(API.class);
  }
}
