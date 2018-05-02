"use strict";
import Vue from 'vue';
import Vuex from 'vuex';
import Buefy from 'buefy';
import 'buefy/lib/buefy.css'
import App from './App';
import io from 'socket.io-client'
import {store} from './store';

Vue.use(Buefy)
Vue.config.productionTip = false;

new Vue({
  el: '#app',
  store,
  components: { App },
  template: '<App/>',
  mounted: function() { 
    // Setup up socket
    let socket = null;
    if (location.port === '8080') {
      // Using development server
      socket = io.connect('http://localhost:5000');
    } else {
      // Running as webapp
      socket = io.connect('http://' + document.domain  + ':' + location.port);
    }
    store.commit('setSocket', socket);

    socket.on('loggingState', (data) => {
      //console.log(data);
      this.$store.commit('setLoggingState', data);
    });

    socket.on('data', (data) => {
      //console.log(JSON.stringify(data));
      this.$store.commit('setSensorData',data);
    });

    socket.on('datetime', (data) => {
      //console.log(JSON.stringify(data));
      this.$store.commit('setDateTime', data.datetime);
    });
  }
})
