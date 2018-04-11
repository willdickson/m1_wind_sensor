<template> 
  <div class="wind-speed-gauge">
    <canvas 
      v-bind:data-value="speedMilesPerHour"
      id = "wind-speed-gauge"
      data-type="radial-gauge"
      data-width="400"
      data-height="400"
      data-units="mph"
      data-min-value="0"
      data-max-value="10"
      data-major-ticks="0,1,2,3,4,5,6,7,8,9,10"
      data-minor-ticks="0.1"
      data-stroke-ticks="true"
      data-highlights='[
      {"from": 8, "to": 10, "color": "rgba(200, 50, 50, .75)"}
      ]'
      data-color-plate="#fff"
      data-border-shadow-width="0"
      data-borders="true"
      data-needle-type="arrow"
      data-needle-width="2"
      data-needle-circle-size="7"
      data-needle-circle-outer="true"
      data-needle-circle-inner="false"
      data-value-dec="2"
      data-value-int="1"
      data-animation="false"
      ></canvas>

  </div>
</template>

<script>

import {mapState} from 'vuex';
const canvasGauges = require('canvas-gauges');

export default {
  name: 'WindSpeedGauge',
  data () {
    return {}
  },
  computed: {
    speedMilesPerHour() {
      return this.sensorData.speedMilesPerHour.toFixed(2);
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
