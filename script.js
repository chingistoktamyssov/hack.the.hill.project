let x = Math.floor(Math.random() * 150); // Random number between 0 and 150
const numberDisplay = document.getElementById('numberDisplay');
const body = document.body;

function updateBackgroundColor() {
    if (x > 100) {
        body.style.backgroundColor = 'red';
    } else if (x < 75) {
        body.style.backgroundColor = 'blue';
    } else {
        body.style.backgroundColor = 'green';
    }
}

numberDisplay.textContent = x;
updateBackgroundColor();