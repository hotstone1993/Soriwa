package com.newstone.soriwa.demo

import android.os.Bundle
import android.view.View
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

import com.newstone.soriwa.Soriwa

class MainActivity : AppCompatActivity() {
    lateinit var processor: Soriwa
    lateinit var playBtn: Button
    
    override fun onStart() {
        processor = Soriwa()
        processor.init()
        super.onStart()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.layout)

        playBtn = findViewById<Button>(R.id.playBtn)
        playBtn.setOnClickListener { processor.play(0, 0) }
    }
}