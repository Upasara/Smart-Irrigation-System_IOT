


package com.example.myapplication;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;

public class Activity2 extends AppCompatActivity {

    TextView a,b,c,d,e;
    Button btn1;
    DatabaseReference reff;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_2);

        a=(TextView) findViewById(R.id.moist);
        b=(TextView) findViewById(R.id.temp);
        c=(TextView) findViewById(R.id.hum);
        d=(TextView) findViewById(R.id.sun);
        e=(TextView) findViewById(R.id.led);
        btn1=(Button) findViewById(R.id.buttonload);

        btn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                reff = FirebaseDatabase.getInstance().getReference().Child("IrrigationSystem");
                reff.addValueEventListener(new ValueEventListener(){
                    @Override
                    public void onDataChange(@NonNull DataSnapshot dataSnapshot){

                        int humidity = (int) dataSnapshot.child("humidity").getValue();
                        String led = dataSnapshot.child("led").getValue().toString();
                        int  moisture = (int) dataSnapshot.child("moisture").getValue();
                        int sunlight = (int) dataSnapshot.child("sunlight").getValue();
                        int temperature = (int) dataSnapshot.child("temperature").getValue();
                        a.setText(moisture);
                        b.setText(temperature);
                        c.setText(humidity);
                        d.setText(sunlight);
                        e.setText(led);

                    }
                    @Override
                    public void onCancelled(@NonNull DatabaseError databaseError)
                });
            }
        });

    }
}