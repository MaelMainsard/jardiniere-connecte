
import { initializeApp } from "firebase/app";
import { getDatabase } from "firebase/database";

const firebaseConfig = {
    apiKey: "AIzaSyBiBaPZsKrFY7om8_myBmOomVgpMgzvF2E",
    authDomain: "jardiniere-b4923.firebaseapp.com",
    databaseURL: "https://jardiniere-b4923-default-rtdb.europe-west1.firebasedatabase.app",
    projectId: "jardiniere-b4923",
    storageBucket: "jardiniere-b4923.appspot.com",
    messagingSenderId: "275677001513",
    appId: "1:275677001513:web:deb6dba4599d898ddbe938"
};

const app = initializeApp(firebaseConfig);
export const db = getDatabase(app);