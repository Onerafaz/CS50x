// Check for username validity
document.addEventListener('DOMContentLoaded', function() {
  const usernameInput = document.querySelector('#userEmail');
  const usernameMessage = document.querySelector('.userEmail-message');
  const registerForm = document.querySelector('form');

  usernameInput.addEventListener('blur', function() {
    const username = this.value;
    fetch('/check?userEmail=' + username)
      .then(response => response.json())
      .then(result => {
        if (!result.available) {
          usernameMessage.textContent = 'Username is not available';
          usernameMessage.style.color = 'red';
        } else {
          usernameMessage.textContent = '';
          usernameMessage.style.color = '';
        }
      })
      .catch(error => {
        console.error('Fetch error:', error);
      });
  });

  registerForm.addEventListener('submit', function(event) {
    const username = usernameInput.value;
    fetch('/check?username=' + username)
      .then(response => response.json())
      .then(result => {
        if (!result.available) {
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
