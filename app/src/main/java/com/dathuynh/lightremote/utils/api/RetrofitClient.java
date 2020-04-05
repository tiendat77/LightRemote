package com.dathuynh.lightremote.utils.api;

import java.util.concurrent.TimeUnit;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;
import okhttp3.OkHttpClient;

public class RetrofitClient {
  private static Retrofit retrofit = null;

  public static Retrofit getRetrofitService(String baseurl) {
    OkHttpClient builder = new OkHttpClient.Builder()
        .readTimeout(5000, TimeUnit.MILLISECONDS)
        .writeTimeout(5000, TimeUnit.MILLISECONDS)
        .connectTimeout(10000, TimeUnit.MILLISECONDS)
        .retryOnConnectionFailure(true)
        .build();

    Gson gson = new GsonBuilder().setLenient().create();

    retrofit = new Retrofit.Builder()
        .baseUrl(baseurl)
        .client(builder)
        .addConverterFactory(GsonConverterFactory.create(gson))
        .build();

    return retrofit;
  }

}
