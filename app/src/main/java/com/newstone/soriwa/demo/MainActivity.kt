package com.newstone.soriwa.demo

import android.Manifest
import android.content.pm.PackageManager
import android.database.Observable
import android.os.Bundle
import android.widget.Button
import android.widget.SeekBar
import android.widget.TextView
import androidx.activity.viewModels
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.lifecycle.observe
import com.newstone.soriwa.Configuration

import com.newstone.soriwa.Soriwa
import com.newstone.soriwa.Soriwa.CustomRendererListener



class MainActivity : AppCompatActivity() {
    val kReadExternalStorageRequest = 100

    val model: MainViewModel by viewModels()
    lateinit var playBtns: MutableList<Button>
    lateinit var stopBtns: MutableList<Button>
    var idMap: MutableMap<String, Int> = mutableMapOf()
    override fun onStart() {
        checkPermissions()
        val config = Configuration()
        config.playMode = Configuration.PlayMode.Repeat.ordinal
        config.playMode = Configuration.SharingMode.Exclusive.ordinal
        config.frameSize = 1000;

        val id1 = Soriwa.getInstance().addAudio(config, "/sdcard/Gaudio/test.wav")
        idMap.put("test1", id1)
        val id2 = Soriwa.getInstance().addAudio(config, "/sdcard/Gaudio/test.wav")
        idMap.put("test2", id2)
        val id3 = Soriwa.getInstance().addAudio(config, "/sdcard/Gaudio/test.wav")
        idMap.put("test3", id3)

        super.onStart()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.layout)
        val model: MainViewModel by viewModels()

        playBtns = mutableListOf<Button>()
        stopBtns = mutableListOf<Button>()

        for(idx in 1 until 4) {
            val playBtnId = resources.getIdentifier("playBtn" + idx, "id", packageName)
            val playBtn = findViewById<Button>(playBtnId)
            val stopBtnId = resources.getIdentifier("stopBtn" + idx, "id", packageName)
            val stopBtn = findViewById<Button>(stopBtnId)
            playBtn.setOnClickListener { Soriwa.getInstance().play(idMap["test" + idx]?:0) }
            stopBtn.setOnClickListener{ Soriwa.getInstance().stop(idMap["test" + idx]?:0) }

            playBtns.add(playBtn)
            stopBtns.add(stopBtn)
        }

        val textView: TextView = findViewById(R.id.textView)
        val seekBar: SeekBar = findViewById(R.id.custom)

        model.coeff.observe(this) {
            textView.text = it.toString()
        }

        Soriwa.getInstance().setCustomRendererListener( object : CustomRendererListener{
            override fun render(input: FloatArray?, output: FloatArray?, samplePerBlock: Int) {
                for(idx in 0 until samplePerBlock) {
                    output!![idx] = input!![idx] * model.coeff.value!!
                }
            }
        })

        seekBar.progress = seekBar.max
        seekBar.setOnSeekBarChangeListener(object: SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                model.coeff.value = progress.toFloat() / 10.0f
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

