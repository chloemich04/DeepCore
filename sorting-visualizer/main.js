const ARRAY_SIZE = 30;
let array = [];

function generateArray() {
    array = [];
    for (let i = 0; i < ARRAY_SIZE; i++) {
        array.push(Math.floor(Math.random() * 200) + 20);
    }
}

function renderArray() {
    const container = document.getElementById('array-container');
    container.innerHTML = '';
    
    for (let i = 0; i < array.length; i++) {
        const bar = document.createElement('div');
        bar.classList.add('bar');
        bar.style.height = array[i] + 'px';
        container.appendChild(bar);
    }
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function bubbleSort() {
    const bars = document.getElementsByClassName('bar');
    for (let i = 0; i < array.length - 1; i++) {
        for (let j = 0; j < array.length - i - 1; j++) {
            bars[j].classList.add('active');        
            bars[j + 1].classList.add('active');
            await sleep(100);

            if (array[j] > array[j + 1]) {
                [array[j], array[j + 1]] = [array[j + 1], array[j]];
                bars[j].style.height = array[j] + 'px';
                bars[j + 1].style.height = array[j + 1] + 'px';
            }

            bars[j].classList.remove('active');
            bars[j + 1].classList.remove('active');
        }
    }
}

generateArray();
renderArray();
document.getElementById('start-btn').addEventListener('click', bubbleSort);