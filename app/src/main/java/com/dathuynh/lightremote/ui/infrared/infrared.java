package com.dathuynh.lightremote.ui.infrared;

import androidx.lifecycle.ViewModelProviders;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import com.dathuynh.lightremote.R;
import com.dathuynh.lightremote.utils.infrared.ConsumerIrManager;
import com.dathuynh.lightremote.utils.infrared.IrCommand;
import com.google.android.material.floatingactionbutton.FloatingActionButton;

public class infrared extends Fragment implements View.OnClickListener {

  // DECLARE VARIABLES
  private InfraredViewModel mViewModel;
  private static final String TAG = "INFRARED FRAGMENT";
  private ConsumerIrManager irManager;

  private FloatingActionButton powerButton;
  private FloatingActionButton muteButton;
  private FloatingActionButton channelUpButton;
  private FloatingActionButton channelDownButton;
  private FloatingActionButton volumeUpButton;
  private FloatingActionButton volumeDownButton;

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

    irManager = ConsumerIrManager.getSupportConsumerIrManager(getContext());

    // Check whether IrEmitter is avaiable on the device.
    if (!irManager.hasIrEmitter()) {
      Log.e(TAG, "Cannot found IR Emitter on the device");
      this.pushNotify("Cannot found IR Emitter on the device");
    }
  }

  @Override
  public void onClick(View v) {
    switch (v.getId()) {
      case R.id.infrared_button_func1:
        transmitProton(Constant.CMD_POWER);
        break;

      case R.id.infrared_button_func2:
        transmitProton(Constant.CMD_OK);
        break;

      case R.id.infrared_button_func3:
        transmitRC5(0xDF238C7);
        break;

      case R.id.infrared_button_func4:
        transmitNEC(0xA10C0807);
        break;

      case R.id.infrared_button_func5:
        break;

      case R.id.infrared_button_func6:
        break;

      default:
        pushNotify("Command not found!");
        break;
    }
  }

  // INIT
  private void initView(View view) {
    powerButton = view.findViewById(R.id.infrared_button_func1);
    muteButton = view.findViewById(R.id.infrared_button_func2);
    channelUpButton = view.findViewById(R.id.infrared_button_func3);
    channelDownButton = view.findViewById(R.id.infrared_button_func4);
    volumeUpButton = view.findViewById(R.id.infrared_button_func5);
    volumeDownButton = view.findViewById(R.id.infrared_button_func6);

    powerButton.setImageResource(R.drawable.ic_power);
    muteButton.setImageResource(R.drawable.ic_mute);
    channelUpButton.setImageResource(R.drawable.ic_channel_up);
    channelDownButton.setImageResource(R.drawable.ic_channel_down);
    volumeUpButton.setImageResource(R.drawable.ic_volume_up);
    volumeDownButton.setImageResource(R.drawable.ic_volume_down);
  }

  private void initListener() {
    powerButton.setOnClickListener(this);
    muteButton.setOnClickListener(this);
    channelUpButton.setOnClickListener(this);
    channelDownButton.setOnClickListener(this);
    volumeDownButton.setOnClickListener(this);
    volumeDownButton.setOnClickListener(this);
  }

  // HANDLER
  private void transmitProton(String command) {
    IrCommand prontoCommand = IrCommand.Pronto.buildPronto(command);
    irManager.transmit(prontoCommand.frequency, prontoCommand.pattern);
  }

  private void transmitRC5(long command) {
    IrCommand RC5Command = IrCommand.RC5.buildRC5(20, command);
    irManager.transmit(RC5Command.frequency, RC5Command.pattern);
  }

  private void transmitNEC(int command) {
    IrCommand necCommand = IrCommand.NEC.buildNEC(32, command);
    irManager.transmit(necCommand.frequency, necCommand.pattern);
  }

  // UTILS
  private void pushNotify(String message) {
    Toast.makeText(getContext(), message, Toast.LENGTH_SHORT).show();
  }

}
