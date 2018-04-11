<template> 
  <div class="datetime-display">
    <p class="has-text-left"> <strong> {{datetime}} </strong></p>
  </div>
</template>

<script>
export default {
  name: 'DateTimeDisplay',
  data () {
    return {}
  },
  computed: {
    datetime() {
      return this.$store.state.datetime;
    }
  }
}
</script>

<style scoped>
</style>
