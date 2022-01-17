function validation()  {  
    var username = document.loginForm.defaultUsername.value;  
    var password = document.loginForm.defaultPassword.value;  
        
    if(username.length == "" && password.length == "") {  
        alert("User Name and Password fields are empty");  
        return false;  
    }  
    else {  
        if(username.length == "") {  
            alert("User Name is empty");  
            return false;  
        }   

        if (password.length == "") {  
            alert("Password field is empty");  
            return false;  
        }  
    }                             
} 
