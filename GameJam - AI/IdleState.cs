using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IdleState : State
{
   
    public ChaseState chase;

    public Transform player;

    float minimumDetectionAngle = -50f;
    float maximumDetectionAngle = 50f;

    private void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player").transform;
    }

    public override State RunState()
    {
        if (DetectsPlayer())
        {
            // detect the player 
            // raycast? maybe a few seconds of seeing will result in chase - not instant


            return chase;
        }
        else
        {
            // just patrol the scene
            // maybe follow waypoints - fixed path

            return this;
        }
    }


    public bool DetectsPlayer()
    {

        Vector3 targetDirection = player.position - transform.position;

        float fov = Vector3.Angle(targetDirection, transform.forward);

        RaycastHit hit;
        // compare angle between enemy looking forward and targets position
        // if player is outside of enemies fov he stays undetected
        // also use raycast to determin if AI can actually see the player
        if (fov > minimumDetectionAngle && fov < maximumDetectionAngle &&
            Physics.Raycast(transform.position, player.position - transform.position, out hit, 15f))
        {

            if (hit.collider.CompareTag("Player"))
            {

                return true;
            }
            else
            {

                return false;
            }
           
        }
        else
        {
            return false;
        }
    }
    // add detection meter? like on detection + x * deltaTime and if reaches X -> detected

 
}
