using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StateMenager : MonoBehaviour
{

    public State currentState;

    // Update is called once per frame
    void Update()
    {
        RunStateMachine(); 
    }

    private void RunStateMachine()
    {
        State nextState = currentState?.RunState();
        // "?" means that if variable is not null then RunState, if null - ignore

        if (nextState != null)
        {
            // switch to the next state
            SwitchToNextState(nextState);

        }
    }

    private void SwitchToNextState(State state)
    {
        
        currentState = state;
        
    }


}
