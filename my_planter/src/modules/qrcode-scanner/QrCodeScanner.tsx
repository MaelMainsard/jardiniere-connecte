import { useEffect, useRef, useState } from "react";
import { Player } from '@lottiefiles/react-lottie-player';

import QrScanner from "qr-scanner";
import {FontAwesomeIcon} from "@fortawesome/react-fontawesome";
import {faChevronLeft} from "@fortawesome/free-solid-svg-icons";
import {useNavigate} from "react-router-dom";

export const QrCodeScanner = () => {

    // QR States
    const scanner = useRef<QrScanner>();
    const videoEl = useRef<HTMLVideoElement>(null);
    const [qrOn, setQrOn] = useState<boolean>(true);

    const navigate = useNavigate ();


    // Result
    const [scannedResult, setScannedResult] = useState<string | undefined>("");

    // Success
    const onScanSuccess = (result: QrScanner.ScanResult) => {
        setScannedResult(result?.data);
    };

    // Fail
    const onScanFail = (err: string | Error) => {
        // 🖨 Print the "err" to browser console.
        //console.log(err);
    };

    useEffect(() => {
        if (videoEl?.current && !scanner.current) {
            // 👉 Instantiate the QR Scanner
            scanner.current = new QrScanner(videoEl?.current, onScanSuccess, {
                onDecodeError: onScanFail,
                // 📷 This is the camera facing mode. In mobile devices, "environment" means back camera and "user" means front camera.
                preferredCamera: "environment",
                // 🖼 This will help us position our "QrFrame.svg" so that user can only scan when qr code is put in between our QrFrame.svg.
                highlightScanRegion: true,
                // 🔥 This will produce a yellow (default color) outline around the qr code that we scan, showing a proof that our qr-scanner is scanning that qr code.
                highlightCodeOutline: true,
                // 📦 A custom div which will pair with "highlightScanRegion" option above 👆. This gives us full control over our scan region.
                overlay: undefined,
            });

            // 🚀 Start QR Scanner
            scanner?.current
                ?.start()
                .then(() => setQrOn(true))
                .catch((err) => {
                    if (err) setQrOn(false);
                });
        }

        // 🧹 Clean up on unmount.
        // 🚨 This removes the QR Scanner from rendering and using camera when it is closed or removed from the UI.
        return () => {
            if (!videoEl?.current) {
                scanner?.current?.stop();
            }
        };
    }, []);


    return (

        <div className="bg-white flex flex-col w-screen h-screen justify-between">

            <button className="pl-10 flex mt-12" onClick={() => {
                navigate('/')
            }}>
                <FontAwesomeIcon icon={faChevronLeft} className="text-neutral h-5 mt-0.5"/>
                <div className="w-5"></div>
                <h1 className="text-neutral">My planters</h1>
            </button>

            <div className="flex flex-col items-center">
                {!qrOn ? (
                    <div className="w-80 h-80 rounded-3xl mb-5">
                        <Player
                            src='https://lottie.host/1a7ff2f9-efe8-4e17-ae4d-3f4475229a69/oB9niqp5Zw.json'
                            className="player"
                            loop
                            autoplay
                        />
                    </div>
                ) : (
                    <video ref={videoEl} className="object-cover w-80 h-80 rounded-3xl mb-5"></video>
                )}
                <input type="text" placeholder="Type the id here" value={scannedResult} className="input input-bordered w-80 mb-3"/>
                <button className="btn w-80">Next</button>
            </div>

            <div></div>
            <div></div>


        </div>
    );
}