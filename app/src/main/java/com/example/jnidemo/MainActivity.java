package com.example.jnidemo;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("jnidemo");
    }

    public native boolean checkNativeSecurity();
    public native String getSecureMessage();
    public native int secureFactorial(int number);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tvStatus = findViewById(R.id.tvStatus);
        TextView tvMessage = findViewById(R.id.tvMessage);
        TextView tvFactorial = findViewById(R.id.tvFactorial);

        boolean suspicious = checkNativeSecurity();

        if (suspicious) {
            tvStatus.setText("⚠ Environnement suspect détecté");
            tvStatus.setTextColor(Color.parseColor("#DC2626"));

            tvMessage.setText("Fonction JNI protégée");
            tvFactorial.setText("Calcul natif désactivé");
        } else {
            tvStatus.setText("✅ Environnement sécurisé");
            tvStatus.setTextColor(Color.parseColor("#16A34A"));

            tvMessage.setText(getSecureMessage());

            int result = secureFactorial(10);
            tvFactorial.setText("Factoriel de 10 = " + result);
        }
    }
}