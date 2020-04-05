package com.dathuynh.lightremote.ui.infrared;

import androidx.lifecycle.ViewModelProviders;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.dathuynh.lightremote.R;

public class infrared extends Fragment {

  // DECLARE VARIABLES
  private InfraredViewModel mViewModel;

  public static infrared newInstance() {
    return new infrared();
  }

  @Override
  public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                           @Nullable Bundle savedInstanceState) {

    View view = inflater.inflate(R.layout.infrared_fragment, container, false);

    // INITIALIZE
    initView(view);
    initListener();

    return view;
  }

  @Override
  public void onActivityCreated(@Nullable Bundle savedInstanceState) {
    super.onActivityCreated(savedInstanceState);
    mViewModel = ViewModelProviders.of(this).get(InfraredViewModel.class);
    // TODO: Use the ViewModel
  }

  // INIT
  private void initView(View view) {

  }

  private void initListener() {
  }

  // HANDLER


}
