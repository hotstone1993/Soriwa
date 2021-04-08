package com.newstone.soriwa.demo

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel

class MainViewModel : ViewModel() {
    var coeff : MutableLiveData<Float> = MutableLiveData()
}