//
//  ViewController.swift
//  ImageClassificationNN
//
//  Created by Daniel Solovich on 12/10/17.
//  Copyright © 2017 Daniel Solovich. All rights reserved.
//

import UIKit
import Darwin

class ViewController: UIViewController {

    var gues: Int32!

    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        let path = getDocumentsDirectory().path + "/Image.png"
        print(path)
        printRelativePath()
    }
    

    
    @IBOutlet weak var GuesLabel: UILabel!
    
    @IBAction func recognaizeImage(_ sender: Any) {
        saveImageFromDrawView(); 
        let path = getDocumentsDirectory().path + "/Image.png"
        self.gues = getNeuralNetResult(path)
        if self.gues == 404 {
            GuesLabel.text = String("No image was found") 
        } else {
            GuesLabel.text = String(self.gues)
        }
    }
    
    @IBOutlet weak var DrawingView: DrawingView!
    @IBAction func clearDrawView(_ sender: Any) {
        DrawingView.clearCanvas()
        GuesLabel.text = "" 
    }
    
    func saveImageFromDrawView() {
        let imageForSaving = scaleImage(image: DrawingView.convertDrawingViewIntoImage(), to: CGSize(width:28, height: 28))
        if let data = UIImagePNGRepresentation(imageForSaving) {
            let filename = getDocumentsDirectory().appendingPathComponent("Image.png")
            try? data.write(to: filename)
        }
    }
    
    func scaleImage(image: UIImage, to size: CGSize) -> UIImage {
        UIGraphicsBeginImageContext(size)
        image.draw(in: CGRect(x: 0, y: 0, width: size.width, height: size.height))
        let newimage = UIGraphicsGetImageFromCurrentImageContext()
        UIGraphicsEndImageContext()
        return newimage!;
    }
    
    func getDocumentsDirectory() -> URL {
        let paths = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)
        return paths[0]
    }

    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    @IBAction func moveToTrainView(_ sender: Any) {
        let storyboard = UIStoryboard(name: "Train", bundle: nil)
        let vc = storyboard.instantiateViewController(withIdentifier: "trainVC") as UIViewController
        present(vc, animated: true, completion: nil)
    }
    
}


