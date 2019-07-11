package com.zego.audioroomdemo.adapters;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.zego.audioroomdemo.MainActivity;
import com.zego.audioroomdemo.R;
import com.zego.audioroomdemo.entity.ZegoUserInfo;
import com.zego.zegoaudioroom.ZegoAudioStream;
import com.zego.zegoavkit2.soundlevel.ZegoSoundLevelInfo;
import com.zego.zegoliveroom.entity.ZegoUserState;

import java.math.RoundingMode;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by zego on 2018/6/27.
 */

public class RecyclerGridViewAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

    private Context mContext;
    private ZegoUserState selfZegoUser = null;
    private volatile List<ZegoUserInfo> zegoUserList = new ArrayList<>();
    private List<MyHolder> myHolders = new ArrayList<>();

    private NumberFormat numberFormat = NumberFormat.getNumberInstance();
    private RecyclerView mUserRecyclerView;

    public RecyclerGridViewAdapter(Context context, RecyclerView userRecyclerView) {
        this.mContext = context;
        this.mUserRecyclerView = userRecyclerView;
        numberFormat.setMaximumFractionDigits(2);
        numberFormat.setRoundingMode(RoundingMode.UP);
    }

    public void setSelfZegoUser(ZegoUserState selfZegoUser) {
        this.selfZegoUser = selfZegoUser;
    }

    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(mContext).inflate(R.layout.stream_info, null);
        MyHolder holder = new MyHolder(view);
        myHolders.add(holder);
        return holder;
    }

    public void addUser(ZegoUserState zegoUserState) {
        synchronized (this) {
            for (ZegoUserInfo zegoUserInfo : zegoUserList) {
                if (zegoUserInfo.userName.equals(zegoUserState.userName)) {
                    return;
                }
            }
            ZegoUserInfo mZegoUserInfo = new ZegoUserInfo();
            mZegoUserInfo.userID = zegoUserState.userID;
            mZegoUserInfo.userName = zegoUserState.userName;
            zegoUserList.add(mZegoUserInfo);
            uiThreadNotifyDataSetChanged();
        }
    }

    public void removeUser(ZegoUserState zegoUserState) {
        synchronized (this) {
            int zegoUserIndex = -1;
            for (int i = 0; i < zegoUserList.size(); i++) {
                ZegoUserInfo zegoUser = zegoUserList.get(i);
                if (zegoUser.userName.equals(zegoUserState.userName) && zegoUser.userID.equals(zegoUserState.userID)) {
                    zegoUserIndex = i;
                }
            }
            if (zegoUserIndex != -1) {
                zegoUserList.remove(zegoUserIndex);
            }
            uiThreadNotifyDataSetChanged();
        }
    }

    public void removeUser(ZegoUserState zegoUserState, ZegoAudioStream zegoAudioStream) {
        synchronized (this) {
            int zegoUserIndex = -1;
            for (int i = 0; i < zegoUserList.size(); i++) {
                ZegoUserInfo zegoUser = zegoUserList.get(i);
                if (zegoUser.userName.equals(zegoUserState.userName) && zegoUser.userID.equals(zegoUserState.userID)) {
                    if (zegoUser.streamID != null && zegoUser.streamID.equals(zegoAudioStream.getStreamId())) {
                        zegoUserIndex = i;
                    }
                }
            }
            if (zegoUserIndex != -1) {
                zegoUserList.remove(zegoUserIndex);
            }
            uiThreadNotifyDataSetChanged();
        }
    }


    private int[] background = {R.mipmap.disable_mic, R.mipmap.disconnect, R.mipmap.sound_waves, R.mipmap.begin_retry};

    @Override
    public void onBindViewHolder(RecyclerView.ViewHolder holder, int position) {
        MyHolder myHolder = (MyHolder) holder;
        if (selfZegoUser != null && zegoUserList.get(position).userName.equals(selfZegoUser.userName)) {
            myHolder.textViewName.setText(mContext.getString(R.string.zg_text_self_user_name, zegoUserList.get(position).userName));
        } else {
            myHolder.textViewName.setText(zegoUserList.get(position).userName);
        }

        if (zegoUserList.get(position).audioState == 0) {
            myHolder.audioState.setBackgroundResource(background[2]);
            if (!zegoUserList.get(position).mute) {
                // 关闭麦克风
                myHolder.audioState.setBackgroundResource(background[0]);
                myHolder.progressBar.setVisibility(View.INVISIBLE);
            } else {
                // 开启麦克风
                myHolder.audioState.setBackgroundResource(background[2]);
                myHolder.progressBar.setVisibility(View.VISIBLE);
                myHolder.progressBar.setProgress(zegoUserList.get(position).progress);
            }
        } else if (zegoUserList.get(position).audioState == 1) {
            // 断网
            myHolder.audioState.setBackgroundResource(background[1]);
        } else if (zegoUserList.get(position).audioState == 2) {
            // 重试中
            myHolder.audioState.setBackgroundResource(background[3]);
        }

        if (zegoUserList.get(position).streamID != null) {
            myHolder.mView.setTag(zegoUserList.get(position).streamID);
        }

    }

    @Override
    public int getItemCount() {
        return zegoUserList.size();
    }

    /**
     * 用户绑定流ID
     */
    public void bindUserInfoStreamID(final ZegoAudioStream zegoAudioStream) {
        synchronized (this) {

            for (ZegoUserInfo zegoUserInfo : zegoUserList) {
                if (zegoAudioStream.getStreamId() != null && zegoUserInfo.userID.equals(zegoAudioStream.getUserId()) && zegoUserInfo.userName.equals(zegoAudioStream.getUserName())) {
                    zegoUserInfo.streamID = zegoAudioStream.getStreamId();
                    break;
                }
            }
            uiThreadNotifyDataSetChanged();
        }
    }

    /**
     * 音浪
     *
     * @param zegoSoundLevelInfo
     */
    public void soundLevelUpdate(ZegoSoundLevelInfo zegoSoundLevelInfo) {
        for (ZegoUserInfo zegoUserInfo : zegoUserList) {
            if (zegoUserInfo.streamID != null && zegoUserInfo.streamID.equals(zegoSoundLevelInfo.streamID)) {
                zegoUserInfo.progress = ((int) (zegoSoundLevelInfo.soundLevel));
                break;
            }
        }
        uiThreadNotifyDataSetChanged();
    }

    public void updateMuteState(boolean mute, String userName) {
        synchronized (this) {
            for (ZegoUserInfo zegoUserInfo : zegoUserList) {
                if (zegoUserInfo.userName != null && zegoUserInfo.userName.equals(userName)) {
                    zegoUserInfo.mute = mute;
                    break;
                }
            }
            uiThreadNotifyDataSetChanged();
        }
    }

    public void uiThreadNotifyDataSetChanged() {
        mUserRecyclerView.post(new Runnable() {
            @Override
            public void run() {
                notifyDataSetChanged();
            }
        });
    }

    public void streamStateUpdate(int stateCode, ZegoAudioStream zegoAudioStream) {
        synchronized (this) {
            for (ZegoUserInfo zegoUserInfo : zegoUserList) {
                if (zegoUserInfo.streamID != null && zegoUserInfo.streamID.equals(zegoAudioStream.getStreamId())) {
                    zegoUserInfo.audioState = stateCode;
                    break;
                }
            }
        }
        uiThreadNotifyDataSetChanged();
    }

    public void streamStateUpdateAll(int stateCode) {
        synchronized (this) {
            for (ZegoUserInfo zegoUserInfo : zegoUserList) {
                zegoUserInfo.audioState = stateCode;
                break;
            }
        }
        uiThreadNotifyDataSetChanged();
    }


    @SuppressLint("StringFormatInvalid")
    public void updateQualityUpdate(String streamId, CommonStreamQuality zegoStreamQuality) {
        for (MyHolder myHolder : myHolders) {
            Object object = myHolder.mView.getTag();
            if (object != null && streamId != null && streamId.equals(object.toString())) {
                Double audioBreakRate = zegoStreamQuality.audioBreakRate;
                int rtt = zegoStreamQuality.rtt;
                int pktLostRate = (int) (zegoStreamQuality.pktLostRate / (2.6));
                myHolder.textViewCard_frame_rate.setText(audioBreakRate == -1 ? "" : mContext.getString(R.string.zg_btn_text_audio_break_rate, numberFormat.format(audioBreakRate)));
                myHolder.textViewDelay.setText(mContext.getString(R.string.zg_btn_text_delay, rtt));
                myHolder.textViewPacket_loss_rate.setText(mContext.getString(R.string.zg_btn_text_packet_loss_rate, pktLostRate));
                break;
            }
        }
    }

    public static class CommonStreamQuality {
        public double audioFps;
        public double videoFps;
        public double vkbps;
        public int rtt;
        public int pktLostRate;
        public int quality;
        public int width;
        public int height;
        public double audioBreakRate;
    }

    // 定义内部类继承ViewHolder
    class MyHolder extends RecyclerView.ViewHolder {
        TextView textViewName;
        TextView textViewDelay;
        TextView textViewCard_frame_rate;
        TextView textViewPacket_loss_rate;
        ProgressBar progressBar;
        ImageView audioState;
        View mView;

        public MyHolder(View view) {
            super(view);
            this.mView = view;
            textViewName = (TextView) view.findViewById(R.id.name);
            textViewDelay = (TextView) view.findViewById(R.id.delay);
            textViewCard_frame_rate = (TextView) view.findViewById(R.id.card_frame_rate);
            textViewPacket_loss_rate = (TextView) view.findViewById(R.id.packet_loss_rate);
            progressBar = (ProgressBar) view.findViewById(R.id.progressBar);
            audioState = (ImageView) view.findViewById(R.id.audio_state);
        }
    }
}
