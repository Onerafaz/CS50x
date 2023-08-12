// Wait for the DOM to be fully loaded
document.addEventListener('DOMContentLoaded', function() {
  // Add a click event listener to the "Submit" button
  document.getElementById('button-addon2').addEventListener('click', function() {
    // Get the text from the textarea and input fields
    var textareaValue = document.getElementById('exampleFormControlTextarea1').value;
    var inputEmail = document.querySelector('.form-control[type="text"]').value;

    // Display an alert with the input values
    alert('Submitted!\nTextarea value: ' + textareaValue + '\nEmail: ' + inputEmail);
  });
});