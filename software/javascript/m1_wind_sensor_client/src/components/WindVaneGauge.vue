<template> 
  <div class="wind-vane-gauge">
    <canvas 
      id = "wind-vane-gauge"
      v-bind:data-value="angle"
      data-type="radial-gauge"
      data-width = "300"
      data-height = "300"
      data-min-value="0"
      data-max-value="360"
      data-major-ticks="N,NE,E,SE,S,SW,W,NW,N"
      data-minor-ticks="22"
      data-ticks-angle="360"
      data-start-angle="180"
      data-stroke-ticks="false"
      data-highlights="false"
      data-color-plate="#222"
      data-color-major-ticks="#f5f5f5"
      data-color-minor-ticks="#ddd"
      data-color-numbers="#ccc"
      data-color-needle="rgba(240, 128, 128, 1)"
      data-color-needle-end="rgba(255, 160, 122, .9)"
      data-value-box="true"
      data-value-text-shadow="false"
      data-value-dec="1"
      data-color-circle-inner="#fff"
      data-color-needle-circle-outer="#ccc"
      data-needle-circle-size="15"
      data-needle-circle-outer="false"
      data-animation-rule="linear"
      data-needle-type="line"
      data-needle-start="60"
      data-needle-end="99"
      data-needle-width="3"
      data-borders="true"
      data-border-inner-width="0"
      data-border-middle-width="0"
      data-border-outer-width="10"
      data-color-border-outer="#ccc"
      data-color-border-outer-end="#ccc"
      data-color-needle-shadow-down="#222"
      data-border-shadow-width="0"
      data-animation="false"
      ></canvas>
  </div>
</template>

<script>

import {mapState} from 'vuex';
const canvasGauges = require('canvas-gauges');

export default {
  name: 'WindVaneGauge',
  data () {
    return {}
  },
  computed: {
    angle() {
      return this.sensorData.angleDegree.toFixed(1);
    },
    ...mapState([
      'loggingState',
      'sensorData'
    ])
  },
  mounted: function() {

  }
}
</script>

<style scoped>
</style>
