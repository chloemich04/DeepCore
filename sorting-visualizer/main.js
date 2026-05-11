const ARRAY_SIZE = 30;
let array = [];
let isSorting = false;
let isPaused = false;
let shouldStop = false;
let selectedAlgorithm = 'bubble';
let animationSpeed = 100;

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
    startBtn.textContent = 'Stop Sort';
    startBtn.disabled = false;
    const bars = document.getElementsByClassName('bar');
    for (let i = 0; i < array.length - 1; i++) {
        for (let j = 0; j < array.length - i - 1; j++) {
            while (isPaused) {
                await sleep(animationSpeed);
                if (shouldStop) break;
            }
            if (shouldStop) break;
            bars[j].classList.add('active');
            bars[j + 1].classList.add('active');
            await sleep(animationSpeed);
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
    startBtn.textContent = 'Start Sort';
}

async function insertionSort() {
    isSorting = true;
    isPaused = false;
    shouldStop = false;
    const startBtn = document.getElementById('start-btn');
    startBtn.textContent = 'Stop Sort';
    startBtn.disabled = false;
    const bars = document.getElementsByClassName('bar');
    for (let i = 1; i < array.length; i++) {
        let key = array[i];
        let j = i - 1;
        bars[i].classList.add('active');
        while (j >= 0 && array[j] > key) {
            while (isPaused) {
                await sleep(animationSpeed);
                if (shouldStop) break;
            }
            if (shouldStop) break;
            bars[j].classList.add('active');
            await sleep(animationSpeed);
            array[j + 1] = array[j];
            bars[j + 1].style.height = array[j] + 'px';
            bars[j].classList.remove('active');
            j--;
        }
        array[j + 1] = key;
        bars[j + 1].style.height = key + 'px';
        bars[i].classList.remove('active');
        if (shouldStop) break;
    }
    isSorting = false;
    isPaused = false;
    shouldStop = false;
    startBtn.textContent = 'Start Sort';
}

async function selectionSort() {
    isSorting = true;
    isPaused = false;
    shouldStop = false;
    const startBtn = document.getElementById('start-btn');
    startBtn.textContent = 'Stop Sort';
    startBtn.disabled = false;
    const bars = document.getElementsByClassName('bar');
    for (let i = 0; i < array.length - 1; i++) {
        let minIdx = i;
        bars[i].classList.add('active');
        for (let j = i + 1; j < array.length; j++) {
            while (isPaused) {
                await sleep(animationSpeed);
                if (shouldStop) break;
            }
            if (shouldStop) break;
            bars[j].classList.add('active');
            await sleep(animationSpeed);
            if (array[j] < array[minIdx]) minIdx = j;
            bars[j].classList.remove('active');
        }
        if (minIdx !== i) {
            [array[i], array[minIdx]] = [array[minIdx], array[i]];
            bars[i].style.height = array[i] + 'px';
            bars[minIdx].style.height = array[minIdx] + 'px';
        }
        bars[i].classList.remove('active');
        if (shouldStop) break;
    }
    isSorting = false;
    isPaused = false;
    shouldStop = false;
    startBtn.textContent = 'Start Sort';
}

const algorithms = {
    bubble: {
        name: 'Bubble Sort',
        code: `
async function bubbleSort() {
    for (let i = 0; i < array.length - 1; i++) {
        for (let j = 0; j < array.length - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                [array[j], array[j + 1]] = [array[j + 1], array[j]];
            }
        }
    }
}
`,
        sort: bubbleSort
    },
    insertion: {
        name: 'Insertion Sort',
        code: `
async function insertionSort() {
    for (let i = 1; i < array.length; i++) {
        let key = array[i];
        let j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}
`,
        sort: insertionSort
    },
    selection: {
        name: 'Selection Sort',
        code: `
async function selectionSort() {
    for (let i = 0; i < array.length - 1; i++) {
        let minIdx = i;
        for (let j = i + 1; j < array.length; j++) {
            if (array[j] < array[minIdx]) minIdx = j;
        }
        [array[i], array[minIdx]] = [array[minIdx], array[i]];
    }
}
`,
        sort: selectionSort
    }
};

function updateAlgorithm() {
    document.getElementById('code-block').textContent = algorithms[selectedAlgorithm].code;
    document.querySelectorAll('.algo-btn').forEach(btn => {
        btn.classList.toggle('selected', btn.dataset.algo === selectedAlgorithm);
    });
    document.getElementById('start-btn').textContent = 'Start Sort';
}

generateArray();
renderArray();
updateAlgorithm();

document.getElementById('start-btn').addEventListener('click', function() {
    if (!isSorting) {
        algorithms[selectedAlgorithm].sort();
    } else if (!isPaused) {
        isPaused = true;
        this.textContent = 'Resume Sort';
    } else {
        isPaused = false;
        this.textContent = 'Stop Sort';
    }
});

document.getElementById('reset-btn').addEventListener('click', () => {
    shouldStop = true;
    isPaused = false;
    isSorting = false;
    document.getElementById('start-btn').textContent = 'Start Sort';
    generateArray();
    renderArray();
});

document.querySelectorAll('.algo-btn').forEach(btn => {
    btn.addEventListener('click', () => {
        if (isSorting) return;
        selectedAlgorithm = btn.dataset.algo;
        updateAlgorithm();
        generateArray();
        renderArray();
    });
});

const speedSlider = document.getElementById('speed-slider');
const speedValue = document.getElementById('speed-value');
speedSlider.addEventListener('input', function() {
    animationSpeed = Number(this.value);
    speedValue.textContent = `${animationSpeed}ms`;
});