let arraySize = 30;
let array = [];
let isSorting = false;
let isPaused = false;
let shouldStop = false;
let selectedAlgorithm = 'bubble';
let animationSpeed = 100;
let comparisons = 0;
let swaps = 0;

function generateArray() {
    array = [];
    comparisons = 0;
    swaps = 0;
    updateStatus();

    for (let i = 0; i < arraySize; i++) {
        array.push(Math.floor(Math.random() * 200) + 20);
    }
}

function renderArray() {
    const container = document.getElementById('array-container');
    container.innerHTML = '';
    const paddingTotal = 12;
    const gapPerBar = 4;
    const effectiveWidth = Math.max(40, container.clientWidth - paddingTotal);
    const barWidth = Math.max(2, Math.floor((effectiveWidth - (array.length * gapPerBar)) / array.length));

    for(let i = 0; i < array.length; i++) {
        const bar = document.createElement('div');
        bar.classList.add('bar');
        bar.style.height = array[i] + 'px';
        bar.style.width = `${barWidth}px`;
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
                swaps++;
                bars[j].style.height = array[j] + 'px';
                bars[j + 1].style.height = array[j + 1] + 'px';
            }
            comparisons++;
            updateStatus();
            
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
            swaps++;
            bars[j + 1].style.height = array[j] + 'px';
            bars[j].classList.remove('active');
            j--;
        }
        array[j + 1] = key;
        bars[j + 1].style.height = key + 'px';
        bars[i].classList.remove('active');
        comparisons++;
        updateStatus();
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
            comparisons++;
            bars[j].classList.remove('active');
        }
        if (minIdx !== i) {
            [array[i], array[minIdx]] = [array[minIdx], array[i]];
            swaps++;
            bars[i].style.height = array[i] + 'px';
            bars[minIdx].style.height = array[minIdx] + 'px';
        }
        bars[i].classList.remove('active');
        updateStatus();
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
        description: 'A brute-algorithm that repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order.',
        complexity: {time: 'O(n^2)', space: 'O(1)'},
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
        description: 'Builds the sorted array one item at a time by repeatedly taking the next item and inserting it into the correct position.',
        complexity: {time: 'O(n^2)', space: 'O(1)'},
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
        description: 'Divides the input list into two parts: a sorted sublist and an unsorted sublist and repeatedly selects the smallest element from the unsorted sublist and moves it to the end of the sorted sublist.',
        complexity: {time: 'O(n^2)', space: 'O(1)'},
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
    const algo = algorithms[selectedAlgorithm];
    document.getElementById('code-block').textContent = algo.code;
    document.getElementById('status-description').textContent = algo.description;
    document.getElementById('status-time').textContent = algo.complexity.time;
    document.getElementById('status-space').textContent = algo.complexity.space;

    document.querySelectorAll('.algo-btn').forEach(btn => {
        btn.classList.toggle('selected', btn.dataset.algo === selectedAlgorithm);
    });
    document.getElementById('start-btn').textContent = 'Start Sort'
    updateStatus();
}

function updateStatus() {
    document.getElementById('status-algo').textContent = algorithms[selectedAlgorithm].name;
    document.getElementById('status-text').textContent = isSorting
        ? isPaused ? 'Paused' : 'Sorting'
        : 'Idle';
    
    document.getElementById('status-comparisons').textContent = comparisons;
    document.getElementById('status-swaps').textContent = swaps;
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

document.getElementById('randomize-btn').addEventListener('click', () => {
    shouldStop = true;
    isPaused = false;
    isSorting = false;
    document.getElementById('start-btn').textContent = 'Start Sort';
    generateArray();
    renderArray();
});

const sizeSlider = document.getElementById('size-slider');
const sizeValue = document.getElementById('size-value');
sizeSlider.addEventListener('input', function() {
    arraySize = Number(this.value);
    sizeValue.textContent = arraySize;

    shouldStop = true;
    isPaused = false;
    isSorting = false;
    document.getElementById('start-btn').textContent = 'Start Sort';

    generateArray();
    renderArray();
});