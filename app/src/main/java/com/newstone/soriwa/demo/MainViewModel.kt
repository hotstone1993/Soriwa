package com.newstone.soriwa.demo

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel

class MainViewModel : ViewModel() {
    var idMap: MutableMap<String, Int> = mutableMapOf()
    var coeff : Float = 1.0f
}