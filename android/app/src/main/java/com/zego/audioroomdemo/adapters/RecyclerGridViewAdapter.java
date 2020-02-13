package com.zego.audioroomdemo.adapters;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.zego.audioroomdemo.R;
import com.zego.audioroomdemo.entity.StreamStateBean;

import java.util.List;

/**
 * Created by zego on 2018/6/27.
 */

public class RecyclerGridViewAdapter extends RecyclerView.Adapter<RecyclerGridViewAdapter.MyHolder> {

    private List<StreamStateBean> streamStateBeans;

    public RecyclerGridViewAdapter(List<StreamStateBean> streamStateBeans) {
        this.streamStateBeans = streamStateBeans;
    }

    @Override
    public RecyclerGridViewAdapter.MyHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        return new MyHolder(LayoutInflater.from(parent.getContext()).inflate(R.layout.stream_info, parent, false));
    }

    private int[] background = {R.mipmap.disable_mic, R.mipmap.disconnect, R.mipmap.sound_waves, R.mipmap.begin_retry};

    @Override
    public void onBindViewHolder(RecyclerGridViewAdapter.MyHolder holder, int position) {
        StreamStateBean qualityBean = streamStateBeans.get(position);

        Context context = holder.itemView.getContext();

        // 第一个固定为自己
        if (position == 0) {
            holder.textViewName.setText(context.getString(R.string.zg_text_self_user_name, qualityBean.userName));
        } else {
            holder.textViewName.setText(qualityBean.userName);
        }

        // 正常情况下
        if (qualityBean.connectState == StreamStateBean.ConnectState.COMMON) {
            if (qualityBean.isMuteMic) {
                holder.connectState.setBackgroundResource(background[0]);
                holder.progressBar.setVisibility(View.INVISIBLE);
            } else {
                holder.connectState.setBackgroundResource(background[2]);
                holder.progressBar.setVisibility(View.VISIBLE);
                holder.progressBar.setProgress(qualityBean.soundLevel);
            }
        } else if (qualityBean.connectState == StreamStateBean.ConnectState.DISCONNECT) {
            // 断网
            holder.connectState.setBackgroundResource(background[1]);
        } else if (qualityBean.connectState == StreamStateBean.ConnectState.RECONNECT) {
            // 重试中
            holder.connectState.setBackgroundResource(background[3]);
        }

        holder.textViewDelay.setText(context.getString(R.string.zg_btn_text_delay, qualityBean.rtt));
        holder.textViewCard_frame_rate.setText(qualityBean.audioBreakRate < 0 ? "" : context.getString(R.string.zg_btn_text_audio_break_rate, (int) qualityBean.audioBreakRate)); // TODO
        holder.textViewPacket_loss_rate.setText(context.getString(R.string.zg_btn_text_packet_loss_rate, qualityBean.pktLostRate));
    }

    @Override
    public int getItemCount() {
        return streamStateBeans.size();
    }

    // 定义内部类继承ViewHolder
    class MyHolder extends RecyclerView.ViewHolder {
        TextView textViewName;
        TextView textViewDelay;
        TextView textViewCard_frame_rate;
        TextView textViewPacket_loss_rate;
        ProgressBar progressBar;
        ImageView connectState;

        private MyHolder(View view) {
            super(view);
            textViewName = view.findViewById(R.id.name);
            textViewDelay = view.findViewById(R.id.delay);
            textViewCard_frame_rate = view.findViewById(R.id.card_frame_rate);
            textViewPacket_loss_rate = view.findViewById(R.id.packet_loss_rate);
            progressBar = view.findViewById(R.id.progressBar);
            connectState = view.findViewById(R.id.connect_state);
        }
    }
}
