//
//  TrainView.swift
//  ImageClassificationNN
//
//  Created by Daniel Solovich on 1/19/18.
//  Copyright © 2018 Daniel Solovich. All rights reserved.
//

import UIKit

class TrainView: UIViewController {
    
    
    @IBOutlet weak var numberOfEpoches: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.numberOfEpoches.text = "100"
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    
    @IBAction func goBackToMainView(_ sender: Any) {
        let storyboard = UIStoryboard(name: "Main", bundle: nil)
        let vc = storyboard.instantiateViewController(withIdentifier: "mainVC") as UIViewController
        present(vc, animated: true, completion: nil)
    }
    
    
    @IBAction func trainOnDefaultDataset(_ sender: Any) {
        if let text = self.numberOfEpoches.text {
            let epoches = UInt32(text)
            trainOnDefault(epoches!) 
        }
    }
    
    @IBAction func trainOnFullDataset(_ sender: Any) {
        if let text = self.numberOfEpoches.text {
            let epoches = UInt32(text)
            trainOnUserDataset(epoches!) 
        }
    }
    
    
    @IBAction func createYourOwnDataset(_ sender: Any) {
        let storyboard = UIStoryboard(name: "CreateDataset", bundle: nil)
        let vc = storyboard.instantiateViewController(withIdentifier: "createDatasetVC") as UIViewController
        present(vc, animated: true, completion: nil)
    }
    

}
