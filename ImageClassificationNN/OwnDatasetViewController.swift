//
//  OwnDatasetViewController.swift
//  ImageClassificationNN
//
//  Created by Daniel Solovich on 1/21/18.
//  Copyright © 2018 Daniel Solovich. All rights reserved.
//

import UIKit



class OwnDatasetViewController: UIViewController {
    
    
    @IBOutlet weak var label: UITextField!
    @IBOutlet weak var DrawingView: DrawingView!

    override func viewDidLoad() {
        super.viewDidLoad()
        self.label.text = "Type label here..."
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func goBackToTrainView(_ sender: Any) {
        let storyboard = UIStoryboard(name: "Train", bundle: nil)
        let vc = storyboard.instantiateViewController(withIdentifier: "trainVC") as UIViewController
        present(vc, animated: true, completion: nil)
    }
    
    @IBAction func saveImageInUserDataset(_ sender: Any) {
        if self.label.text != "Type label here..." {
            let imageForSaving = scaleImage(image: DrawingView.convertDrawingViewIntoImage(), to: CGSize(width:28, height: 28))
            if let data = UIImagePNGRepresentation(imageForSaving) {
                let filename = getDocumentsDirectory().appendingPathComponent("Image.png")
                try? data.write(to: filename)
            }
            let path = getDocumentsDirectory().path + "/Image.png"
            let label = Int32(self.label.text!)
            putImageInDataset(path, label!)
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
    
    @IBAction func removeDrawingFromCanvas(_ sender: Any) {
        DrawingView.clearCanvas();
    }
    
    

    

}
