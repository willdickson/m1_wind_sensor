<template> 
  <div class="save-data-switch">
    <div class="field">
      <b-switch 
        v-model="switchState" 
        v-on:input="onSwitchInput"
        type="is-dark" 
        size="is-medium"
        > 
        <strong> {{switchMessage}} &nbsp &nbsp  {{fileName}} &nbsp &nbsp {{sampleInfo}} </strong>
      </b-switch>
    </div>
  </div>
</template>

<script>
"use strict";

import {mapState} from 'vuex';

export default {
  name: 'SaveDataSwitch',
  data () {
    return {
      switchState: false
    }
  },
  computed: {
    switchMessage() { 
      if (this.switchState) {
        return 'Logging On,';
      } else {
        return 'Logging Off';
      }
    },
    fileName() {
      if (this.switchState) {
        return 'filename: ' + this.loggingState.fileName + ','; 
      } else {
        return null;
      }
    },
    sampleInfo() {
      if (this.switchState) {
        return 'samples: ' + this.sensorData.numberOfSamples;
      } else {
        return null;
      }
    },
    ...mapState([
      'loggingState',
      'sensorData'
    ])
  },
  methods: {
    onSwitchInput() {
      console.log('onSwitchInput: ' + this.switchState);
      if (this.switchState) {
        this.$store.state.socket.emit('startLogging', {});
      } else {
        this.$store.state.socket.emit('stopLogging', {});
      }
    }
  },
  watch: {
    loggingState(newLoggingState, oldLoggingState) {
      //console.log('new: ' + JSON.stringify(newLoggingState));
      //console.log('old: ' + JSON.stringify(oldLoggingState));
      this.switchState = newLoggingState.enabled;
    },
  }
}
</script>

<style scoped>
</style>
