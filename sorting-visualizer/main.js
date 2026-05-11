const ARRAY_SIZE = 30;
let array = [];
let isSorting = false;
let isPaused = false;
let shouldStop = false;

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
    isSorting = true;
    isPaused = false;
    shouldStop = false;

    const startBtn = document.getElementById('start-btn');
    startBtn.textContent = 'Sorting...';
    startBtn.disabled = false;

    const bars = document.getElementsByClassName('bar');
    for (let i = 0; i < array.length - 1; i++) {
        for (let j = 0; j < array.length - i - 1; j++) {
            while (isPaused) {
                await sleep(100);
                if (shouldStop) break;
            }
            if (shouldStop) break;

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
        if (shouldStop) break;
    }

    isSorting = false;
    isPaused = false;
    shouldStop = false;
    startBtn.textContent = 'Start Bubble Sort';
}

const bubbleSortCode = `
async function bubbleSort() {
    for (let i = 0; i < array.length - 1; i++) {
        for (let j = 0; j < array.length - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                [array[j], array[j + 1]] = [array[j + 1], array[j]];
            }
        }
    }
}
`;

generateArray();
renderArray();
document.getElementById('start-btn').addEventListener('click', async function() {
    if (!isSorting) {
        bubbleSort();
    }
    else if (!isPaused) {
        isPaused = true;
        this.textContent = 'Resume Sort';
    }
    else {
        isPaused = false;
        this.textContent = 'Stop Sort';
    }
});
document.getElementById('code-block').textContent = bubbleSortCode;
document.getElementById('reset-btn').addEventListener('click', () => {
    shouldStop = true;
    isPaused = false;
    isSorting = false;
    document.getElementById('start-btn').textContent = 'Start Bubble Sort';
    generateArray();
    renderArray();
});