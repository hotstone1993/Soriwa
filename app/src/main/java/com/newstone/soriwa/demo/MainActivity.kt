package com.newstone.soriwa.demo

import android.Manifest
import android.content.pm.PackageManager
import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.newstone.soriwa.Configuration

import com.newstone.soriwa.Soriwa

class MainActivity : AppCompatActivity() {
    val kReadExternalStorageRequest = 100
    lateinit var playBtn: Button
    lateinit var stopBtn: Button
    var idMap: MutableMap<String, Int> = mutableMapOf()
    override fun onStart() {
        checkPermissions()
        Soriwa.getInstance().init()
        val config = Configuration()
        config.playMode = Configuration.PlayMode.Repeat.ordinal
        config.playMode = Configuration.SharingMode.Exclusive.ordinal

        val id = Soriwa.getInstance().addAudio(config, "/sdcard/Gaudio/test.wav")
        idMap.put("test", id)
        super.onStart()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.layout)

        playBtn = findViewById(R.id.playBtn)
        playBtn.setOnClickListener { Soriwa.getInstance().play(idMap["test"]?:0) }
        stopBtn = findViewById(R.id.stopBtn)
        stopBtn.setOnClickListener{ Soriwa.getInstance().stop(idMap["test"]?:0) }
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