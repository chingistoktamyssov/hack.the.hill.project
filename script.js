let x = Math.floor(Math.random() * 150); // Random number between 0 and 150
const numberDisplay = document.getElementById('numberDisplay');
const rewardMessage = document.getElementById('rewardMessage');
const body = document.body;
const heartImage = document.querySelector('.heart');

function updateHeartImage() {
    if (x > 100) {
        heartImage.src = 'worried.png'; // Path to worried heart image
    } else if (x < 75) {
        heartImage.src = 'calm.png'; // Path to calm heart image
    } else {
        heartImage.src = 'happy.png'; // Path to happy heart image
    }
}

function updateBackgroundColor() {
    if (x > 100) {
        body.style.backgroundColor = 'red';
        rewardMessage.textContent = 'You need to relax and meditate!'; // Message for x > 100
    } else if (x < 75) {
        body.style.backgroundColor = 'blue';
        rewardMessage.textContent = 'Great job! You are calm and relaxed!'; // Rewarding message for x < 75
    } else {
        body.style.backgroundColor = 'green';
        rewardMessage.textContent = 'This is a normal working heart rate. Keep it up!'; // Message for 75 <= x <= 100
    }
}

numberDisplay.textContent = x;
updateBackgroundColor();
updateHeartImage();