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
    lateinit var processor: Soriwa
    lateinit var playBtn: Button
    lateinit var stopBtn: Button
    var id: Int = 0
    override fun onStart() {
        checkPermissions()
        processor = Soriwa()
        processor.init()
        val config = Configuration()
        config.playMode = Configuration.PlayMode.Repeat.ordinal
        config.playMode = Configuration.SharingMode.Exclusive.ordinal

        id = processor.addAudio(config, "/sdcard/Gaudio/test.wav")
        super.onStart()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.layout)

        playBtn = findViewById(R.id.playBtn)
        playBtn.setOnClickListener { processor.play(id) }
        stopBtn = findViewById(R.id.stopBtn)
        stopBtn.setOnClickListener{ processor.stop(id) }
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