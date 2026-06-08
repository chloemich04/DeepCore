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

    const containerWidth = container.clientWidth || 800;
    const containerHeight = container.clientHeight || 300;
    const gapPerBar = 2; // approximate left+right gap in px per bar

    // compute ideal bar width to fit entire array; if too small, we'll keep min width and allow scroll
    const idealBarWidth = Math.floor((containerWidth - (array.length * gapPerBar)) / array.length);
    const minBarWidth = 2;
    const barWidth = Math.max(minBarWidth, idealBarWidth);

    // if bars won't fit, set a min-content width on the inner wrapper to trigger horizontal scroll
    const requiredWidth = (barWidth + gapPerBar) * array.length;
    container.style.minWidth = '0px'; // reset
    if (requiredWidth > containerWidth) {
        container.style.minWidth = requiredWidth + 'px';
    }

    const maxVal = array.length ? Math.max(...array) : 1;
    const verticalPadding = 12;
    for (let i = 0; i < array.length; i++) {
        const bar = document.createElement('div');
        bar.classList.add('bar');

        const height = Math.max(4, Math.round((array[i] / maxVal) * (containerHeight - verticalPadding)));
        bar.style.height = height + 'px';
        bar.style.width = `${barWidth}px`;
        container.appendChild(bar);
    }
}
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

function getBarHeightFromValue(value) {
    const container = document.getElementById('array-container');
    const containerHeight = container.clientHeight || 300;
    const maxVal = array.length ? Math.max(...array) : 1;
    const verticalPadding = 12;
    return Math.max(4, Math.round((value / maxVal) * (containerHeight - verticalPadding)));
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
        bars[array.length - i - 1].classList.add('sorted');
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
        bars[i].classList.add('sorted');
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
        bars[i].classList.add('sorted');
        updateStatus();
        if (shouldStop) break;
    }
    isSorting = false;
    isPaused = false;
    shouldStop = false;
    startBtn.textContent = 'Start Sort';
}

async function partition(low, high) {
    const bars = document.getElementsByClassName('bar');
    const pivotVal = array[high];
    let i = low - 1;

    bars[high].classList.add('active'); // mark pivot
    for (let j = low; j <= high - 1; j++) {
        while (isPaused) {
            await sleep(animationSpeed);
            if (shouldStop) break;
        }
        if (shouldStop) break;

        bars[j].classList.add('active');
        await sleep(animationSpeed);

        comparisons++;
        if (array[j] < pivotVal) {
            i++;
            [array[i], array[j]] = [array[j], array[i]];
            swaps++;

            bars[i].style.height = getBarHeightFromValue(array[i]) + 'px';
            bars[j].style.height = getBarHeightFromValue(array[j]) + 'px';
        }

        updateStatus();
        bars[j].classList.remove('active');
    }

    // put pivot into correct place
    [array[i + 1], array[high]] = [array[high], array[i + 1]];
    swaps++;
    bars[i + 1].style.height = getBarHeightFromValue(array[i + 1]) + 'px';
    bars[high].style.height = getBarHeightFromValue(array[high]) + 'px';
    bars[high].classList.remove('active');

    return i + 1;
}

async function quickSort(low, high) {
    if (low < high) {
        while (isPaused) {
            await sleep(animationSpeed);
            if (shouldStop) return;
        }
        if (shouldStop) return;

        const pi = await partition(low, high);
        const bars = document.getElementsByClassName('bar');
        // optional visual cue: mark pivot position as sorted
        if (pi >= 0 && pi < bars.length) bars[pi].classList.add('sorted');

        await quickSort(low, pi - 1);
        if (shouldStop) return;
        await quickSort(pi + 1, high);
    }
}

async function quickSortStart() {
    isSorting = true;
    isPaused = false;
    shouldStop = false;
    const startBtn = document.getElementById('start-btn');
    startBtn.textContent = 'Stop Sort';
    startBtn.disabled = false;

    await quickSort(0, array.length - 1);

    if (!shouldStop) {
        const bars = document.getElementsByClassName('bar');
        for (let i = 0; i < bars.length; i++) bars[i].classList.add('sorted');
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
    },

    quicksort: {
        name: "Quicksort",
        description: "An efficient divide-and-conquer algorithm that selects a 'pivot' element and partitions the array into two sub-arrays according to whether elements are less than or greater than the pivot, then recursively sorts the sub-arrays.",
        complexity: { time: 'O(n log n)', space: 'O(log n)' },
        code: `
        async function partition(low, high) {
            const pivotVal = array[high];
            let i = low - 1;

            for(let j = low; j<= high - 1; j++) {
                if (array[j] < pivotVal) {
                    i++;
                    [array[i], array[j]] = [array[j], array[i]];
                    swaps++;

                    bars[i].style.height = getBarHeightFromValue(array[i]) + 'px';
                    bars[j].style.height = getBarHeightFromValue(array[j]) + 'px';
                }
            }

            [array[i + 1], array[high]] = [array[high], array[i + 1]];
            
            return i + 1;
        }

        async function quickSort(low, high) {
            if (low < high) {
                const pi = await partition(low, high);

                await quickSort(low, pi - 1);
                await quickSort(pi + 1, high);
            }
        }
        `,
        sort: quickSortStart
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