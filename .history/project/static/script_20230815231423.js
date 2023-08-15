// Check for username validity
document.addEventListener('DOMContentLoaded', function() {
  const userNameInput = document.querySelector('#userName');
  const userEmailInput = document.querySelector('#user-email'); // Assuming the input has an id 'user-email'
  const userNameMessage = document.querySelector('.userName-message');
  const userEmailMessage = document.querySelector('.user-email-message'); // Assuming the message element has a class 'user-email-message'
  const registerForm = document.querySelector('form');

  userNameInput.addEventListener('blur', function() {
    const userName = this.value;
    fetch('/check?userName=' + username)
      .then(response => response.json())
      .then(result => {
        if (!result.available) {
          userNameMessage.textContent = 'Username is not available';
          userNameMessage.style.color = 'red';
        } else {
          userNameMessage.textContent = '';
          userNameMessage.style.color = '';
        }
      })
      .catch(error => {
        console.error('Fetch error:', error);
      });
  });

  userEmailInput.addEventListener('blur', function() {
    const userEmail = this.value;
    fetch('/check?userEmail=' + userEmail) // Adjust the API endpoint to match your server route for email checking
      .then(response => response.json())
      .then(result => {
        if (!result.available) {
          userEmailMessage.textContent = 'Email is not available';
          userEmailMessage.style.color = 'red';
        } else {
          userEmailMessage.textContent = '';
          userEmailMessage.style.color = '';
        }
      })
      .catch(error => {
        console.error('Fetch error:', error);
      });
  });

  registerForm.addEventListener('submit', function(event) {
    const username = usernameInput.value;
    const userEmail = userEmailInput.value;

    fetch('/check?username=' + username + '&userEmail=' + userEmail) // Adjust the API endpoint to match your server route for combined username and email checking
      .then(response => response.json())
      .then(result => {
        if (!result.usernameAvailable || !result.emailAvailable) {
          event.preventDefault(); // Prevent form submission
        }
      })
      .catch(error => {
        console.error('Fetch error:', error);
      });
  });
});

// JavaScript to handle deposit and withdrawal forms
document.addEventListener("DOMContentLoaded", () => {
  const depositInput = document.getElementById("depositInput");
  const withdrawInput = document.getElementById("withdrawInput");
  const depositForm = document.getElementById("depositForm");
  const withdrawForm = document.getElementById("withdrawForm");
  const depositButton = document.getElementById("depositButton");
  const withdrawButton = document.getElementById("withdrawButton");

  depositButton.addEventListener("click", () => {
    if (depositInput.value) {
      depositForm.querySelector('input[name="amount"]').value = depositInput.value;
      depositForm.submit();
    }
  });

  withdrawButton.addEventListener("click", () => {
    if (withdrawInput.value) {
      withdrawForm.querySelector('input[name="amount"]').value = withdrawInput.value;
      withdrawForm.submit();
    }
  });
});

// Table script for sorting
$(document).ready(function() {
  $('#portfolioTable').DataTable({
    paging: true,  // Enable pagination
    searching: true,  // Enable searching
    lengthChange: true,  // Allow changing the number of entries per page
    order: [[3, 'desc']],  // Initial sorting by the fourth column in descending order
  });
});
