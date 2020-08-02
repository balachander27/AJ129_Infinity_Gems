package com.example.upi;

import android.app.PendingIntent;
import android.content.Intent;
import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import android.telephony.SmsManager;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class Message extends
        AppCompatActivity implements View.OnClickListener {
    EditText message;
    Button sendsms;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_message);

        message = (EditText) findViewById(R.id.msg);

        sendsms = (Button) findViewById(R.id.sms);
        sendsms.setOnClickListener(this);
    }

    @Override
    public void onClick(View view)
    {
        String no = "9080996617";
        String msg = message.getText().toString();
        //Getting intent and PendingIntent instance
        if(no.isEmpty()||msg.isEmpty()||no.isEmpty()&&msg.isEmpty())
        {
            Toast.makeText(getApplicationContext(), "Inputs are empty",
                    Toast.LENGTH_LONG).show();
        }
        if(no.length()!=10)
        {
            Toast.makeText(getApplicationContext(), "Invalid Phone number!!",
                    Toast.LENGTH_LONG).show();
        }

        else {
            Intent intent = new Intent
                    (getApplicationContext(),
                            MainActivity.class);
            PendingIntent pi = PendingIntent.getActivity
                    (getApplicationContext(),
                            0, intent, 0);
            SmsManager sms = SmsManager.getDefault();
            sms.sendTextMessage(no, null, msg, pi, null);
            Toast.makeText(getApplicationContext(), "Message Sent successfully!",
                    Toast.LENGTH_LONG).show();
        }
    }
}
