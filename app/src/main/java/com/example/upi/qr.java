package com.example.upi;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class qr extends AppCompatActivity {

    public static TextView result;
    public static String s="";
    Button button,getvalue;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_qr);

        result = (TextView) findViewById(R.id.result);
        button = (Button) findViewById(R.id.button);
        getvalue = (Button) findViewById(R.id.getvalue);

        button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                startActivity(new Intent(getApplicationContext(),ScanCode.class));
            }
        });
        getvalue.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view)
            {
                s=result.getText().toString();
                if(s.isEmpty())
                {
                    Toast.makeText(getApplicationContext(), "Scan QR code properly!!",
                            Toast.LENGTH_LONG).show();
                }
                else
                {
                    Intent i = new Intent(qr.this,FirebaseValues.class);
                    i.putExtra("values",s);
                    startActivityForResult(i,5);

                }
            }
        });
    }
}