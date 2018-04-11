"use strict";
import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex);

export const store = new Vuex.Store({
  state: {
    socket: null,
    datetime: null,
    angle: 0,
    sensorData: {
      time: 0,
      angleDegree: 0,
      speedMetersPerSec: 0,
      speedMilesPerHour: 0,
      numberOfSamples: 0
      
    },
    numberOfSamples: 0,
    loggingState: {
      enabled: false,
      fileName: '',
      directoryExists: false,
    }
  },

  mutations: {

    setSocket(state, socket) {
      state.socket = socket;
    },
    
    setSensorData(state, sensorData) {
      state.sensorData = sensorData;
    },

    setDateTime(state, datetime) {
      state.datetime = datetime;
    },

    setLoggingState(state, loggingState) {
      state.loggingState = loggingState;
    }
  }

})


