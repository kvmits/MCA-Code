function Calendar() {
    const year = document.getElementById('year').value;
    const month = document.getElementById('month').value;
    if (!year || !month || month < 0 || month > 11) {
        alert('Please enter a valid year and month.');
        return;
    }
    const first = new Date(year, month, 1).getDay();
    const days = new Date(year, month + 1, 0).getDate();
    let table = '<table border="1"><tr>' +
        '<th>Sun</th><th>Mon</th><th>Tue</th><th>Wed</th><th>Thu</th><th>Fri</th><th>Sat</th>' +
        '</tr><tr>';
    for (let i = 0; i < first; i++) {
        table += '<td></td>';
    }
    for (let day = 1; day <= days; day++) {
        if ((first + day - 1) % 7 === 0 && day !== 1) {
            table += '</tr><tr>';
        }
        table += '<td>' + day + '</td>';
    }
    table += '</tr></table>';
    document.getElementById('calendar').innerHTML = table;
}