package com.zego.audioroomdemo.activities;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.zego.audioroomdemo.AudioApplication;
import com.zego.audioroomdemo.R;
import com.zego.audioroomdemo.utils.ShareUtils;
import com.zego.zegoliveroom.ZegoLiveRoom;

import java.io.File;
import java.io.FilenameFilter;
import java.util.ArrayList;

import butterknife.Bind;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class LogsActivity extends AppCompatActivity {

    @Bind(R.id.logs_container)
    public ListView logsContainer;

    @Bind(R.id.empty_data_tip)
    public TextView emptyView;

    private BaseAdapter logsAdapter;

    private AudioApplication.ILogUpdateObserver logUpdateObserver= new AudioApplication.ILogUpdateObserver() {
        @Override
        public void onLogAdd(String logMessage) {
            if (logsAdapter != null && !isFinishing()) {
                ((LogsAdapter)logsAdapter).insertItem(logMessage);
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_logs);

        ButterKnife.bind(this);

        logsAdapter = new LogsAdapter();
        logsContainer.setAdapter(logsAdapter);
        logsContainer.setEmptyView(emptyView);

        setTitle(getIntent().getStringExtra("title"));

        ((AudioApplication)getApplication()).registerLogUpdateObserver(logUpdateObserver);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        ((AudioApplication)getApplication()).unregisterLogUpdateObserver(logUpdateObserver);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_logs, menu);
        return true;
    }






    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_upload_log:
                ZegoLiveRoom.uploadLog();
                logsContainer.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        if (!isDestroyed()) {
                            Toast.makeText(AudioApplication.sApplication, getString(R.string.zg_menu_logs_upload_log), Toast.LENGTH_LONG).show();
                        }
                    }
                }, 3000);
                return true;

            case R.id.action_clean_events:
                ((AudioApplication)getApplication()).getLogSet().clear();
                ((LogsAdapter)logsAdapter).reloadData();
                return true;

            default:
                return super.onOptionsItemSelected(item);
        }
    }

    private class LogsAdapter extends BaseAdapter {

        private ArrayList<String> logs;
        private LayoutInflater inflater;

        public LogsAdapter() {
            logs = new ArrayList<>();
            logs.addAll(((AudioApplication)getApplication()).getLogSet());
            inflater = getLayoutInflater();
        }

        @Override
        public int getCount() {
            return logs != null ? logs.size() : 0;
        }

        @Override
        public Object getItem(int position) {
            return logs != null ? logs.get(position) : "";
        }

        @Override
        public long getItemId(int position) {
            return position;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            if (convertView == null) {
                convertView = inflater.inflate(R.layout.widget_list_item, null, false);
            }

            ((TextView)convertView).setText((String)getItem(position));
            return convertView;
        }

        public void insertItem(String logMessage) {
            logs.add(0, logMessage);

            notifyDataSetChanged();
        }

        public void reloadData() {
            logs.clear();
            logs.addAll(((AudioApplication)getApplication()).getLogSet());
            notifyDataSetChanged();
        }
    }
}
