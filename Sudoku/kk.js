function loadSpeed() {
  const selectedspeedIndex = document.getElementById('speedSelector').value - 1;
  if (selectedspeedIndex >= 0) {
      const speed = speeds[selectedspeedIndex];
      for (let row = 0; row < 9; row++) {
          for (let col = 0; col < 9; col++) {
              inputs[row][col].value = ''; // Clear previous inputs
          }
      }
      speed.fixPlaces.forEach((place, index) => {
          const row = place[0];
          const col = place[1];
          inputs[row][col].value = speed.fixNums[index];
      });
  }
}