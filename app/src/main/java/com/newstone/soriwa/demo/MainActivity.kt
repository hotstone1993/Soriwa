package com.newstone.soriwa.demo

import android.Manifest
import android.content.pm.PackageManager
import android.os.Bundle
import android.widget.Button
import android.widget.SeekBar
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.newstone.soriwa.Configuration

import com.newstone.soriwa.Soriwa
import com.newstone.soriwa.Soriwa.CustomRendererListener

class MainActivity : AppCompatActivity() {
    val kReadExternalStorageRequest = 100
    lateinit var playBtn: Button
    lateinit var stopBtn: Button
    var idMap: MutableMap<String, Int> = mutableMapOf()
    var coeff : Float = 1.0f
    override fun onStart() {
        checkPermissions()
        val config = Configuration()
        config.playMode = Configuration.PlayMode.Repeat.ordinal
        config.playMode = Configuration.SharingMode.Exclusive.ordinal
        config.frameSize = 1000;

        val id = Soriwa.getInstance().addAudio(config, "/sdcard/Gaudio/test.wav")
        idMap.put("test", id)
        Soriwa.getInstance().setCustomRendererListener( object : CustomRendererListener{
            override fun render(input: FloatArray?, output: FloatArray?, samplePerBlock: Int) {
                for(idx in 0 until samplePerBlock) {
                    output!![idx] = input!![idx] * coeff
                }
            }
        })
        super.onStart()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.layout)

        playBtn = findViewById(R.id.playBtn)
        playBtn.setOnClickListener { Soriwa.getInstance().play(idMap["test"]?:0) }
        stopBtn = findViewById(R.id.stopBtn)
        stopBtn.setOnClickListener{ Soriwa.getInstance().stop(idMap["test"]?:0) }
        val textView: TextView = findViewById(R.id.textView)
        val seekBar: SeekBar = findViewById(R.id.custom)
        seekBar.progress = seekBar.max

        seekBar.setOnSeekBarChangeListener(object: SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                coeff = progress.toFloat() / 10.0f
                textView.text = coeff.toString()
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {
            }

            override fun onStopTrackingTouch(seekBar: SeekBar?) {
            }

        })
    }

    override fun finishAffinity() {
        super.finishAffinity()
        Soriwa.getInstance().deinit()
    }

    private fun checkPermissions() {
        if (ContextCompat.checkSelfPermission(this,
                Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            if (ActivityCompat.shouldShowRequestPermissionRationale(this,
                    Manifest.permission.READ_EXTERNAL_STORAGE)) {
                ActivityCompat.requestPermissions(this,
                    arrayOf(Manifest.permission.READ_EXTERNAL_STORAGE),
                    kReadExternalStorageRequest)
            } else {
                ActivityCompat.requestPermissions(this,
                    arrayOf(Manifest.permission.READ_EXTERNAL_STORAGE),
                    kReadExternalStorageRequest)
            }
        }
    }
    override fun onRequestPermissionsResult(requestCode: Int,
                                            permissions: Array<String>, grantResults: IntArray) {
        when (requestCode) {
            kReadExternalStorageRequest -> {
                if (grantResults.size > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                } else {
                    android.os.Process.killProcess(android.os.Process.myPid())
                    System.exit(1)
                }
            }
        }
    }
}

