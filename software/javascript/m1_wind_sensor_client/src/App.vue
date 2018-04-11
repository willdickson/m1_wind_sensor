<template>
  <div id="app">

    <!-- <div class="container is-fluid"> -->
    <div class="container">

      <section class="hero is-dark">
        <div class="hero-body">
          <div class="container">
            <h1 class="title">
              M1 Wind Sensor 
            </h1>
            <p class="subtitle">
              <DateTimeDisplay/>
            </p>
          </div>
        </div>
      </section>

      <!-- <div class="section is-fluid level"> -->
      <div class="section level">
        <SaveDataSwitch/>
      </div>


      <div class="is-fluid level"> 
        <div id="gauge-div" class="columns container is-fluid is-8" style="margin:auto;"> 
          <div class="column constainer is-fluid is-7" style="margin:auto;" >
            <WindSpeedGauge/>
          </div>
          <div class="column constainer is-fluid is-7" style="margin:auto;" >
            <WindVaneGauge/>
          </div>
        </div>
      </div>

    </div>
  </div>

</template>

<script>

import WindVaneGauge from './components/WindVaneGauge';
import WindSpeedGauge from './components/WindSpeedGauge';
import DateTimeDisplay from './components/DateTimeDisplay';
import SaveDataSwitch from './components/SaveDataSwitch';

export default {
  name: 'App',
  components: {
    WindVaneGauge,
    WindSpeedGauge,
    DateTimeDisplay,
    SaveDataSwitch
  }
}
</script>

<style>
</style>
