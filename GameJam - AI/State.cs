using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class State : MonoBehaviour
{
    public abstract State RunState();
    // each class that will inherit this class will override this method 
    
    
}
