package com.example.upi;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class FirebaseValues extends AppCompatActivity {

    TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_firebase_values);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        tv = findViewById(R.id.tv);

        Bundle b = getIntent().getExtras();
        String n = b.getString("values");

        tv .setText("Welcome to :"+n);


    }
}