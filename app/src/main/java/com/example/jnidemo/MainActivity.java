package com.example.jnidemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Chargement de la bibliothèque native
    static {
        System.loadLibrary("jnidemo");
    }

    // Méthodes JNI
    public native String getNativeMessage();
    public native int calculateFactorial(int number);
    public native String mirrorText(String text);
    public native int calculateArrayTotal(int[] values);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tvMessage = findViewById(R.id.tvMessage);
        TextView tvFactorial = findViewById(R.id.tvFactorial);
        TextView tvReverse = findViewById(R.id.tvReverse);
        TextView tvArray = findViewById(R.id.tvArray);

        // Message depuis C++
        tvMessage.setText(getNativeMessage());

        // Factoriel
        int fact = calculateFactorial(10);
        tvFactorial.setText("Factoriel de 10 : " + fact);

        // Inversion texte
        String reversed = mirrorText("JNI Android Lab");
        tvReverse.setText("Texte inversé : " + reversed);

        // Tableau
        int[] numbers = {5, 10, 15, 20, 25};
        int sum = calculateArrayTotal(numbers);

        tvArray.setText("Somme du tableau : " + sum);
    }
}