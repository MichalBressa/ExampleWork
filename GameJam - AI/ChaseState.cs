using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChaseState : State
{
    NavMeshAI navAI;
    public bool canAttack;
    public static bool isChasing = false;
    public AttackState attack;
    public IdleState idle;

    public Transform target;


    private void Start()
    {
        target = GameObject.FindGameObjectWithTag("Player").transform;
    }
    public override State RunState()
    {

        // raycast and if false add players pos as new target
        //Physics.Raycast(transform.position, target.position - transform.position, 10f)
        if (idle.DetectsPlayer())
        {
            
            NavMeshAI.isPatrolling = false;

            if (CanAttack())
            {
                // player in attack range
                return attack;
            }
            else
            {
                // keep chasing player
                return this;
                
            }
        }
        else
        {
            /*
            navAI.AddLastKnownPos(target);

            if (Vector3.Distance(transform.position, navAI.GetLastPos().position) < 0.5f || Vector3.Distance(transform.position, target.position) > 10f)
            {
                return idle;
            }
            // to to last seen location -> add waypoint to Waypoints list and set it to current active target
            // return idle state after a while
               
            */


            NavMeshAI.isPatrolling = true;
            NavMeshAI.GetLastPos();
            return idle;
        }


    }
    public bool CanAttack()
    {
        if (Vector3.Distance(transform.position, target.position) < 2f)
        {
            return true;
        }
        else
        {
            return false;
        }  
    }

}
